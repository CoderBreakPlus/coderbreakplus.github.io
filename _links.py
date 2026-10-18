"""OJ URL rules shared by the dashboard and future import tools."""
import json
import re
from pathlib import Path
from urllib.parse import urlsplit


class LinkResolver:
    def __init__(self, config_path=None):
        path = Path(config_path) if config_path else Path(__file__).with_name('oj.json')
        self.config = json.loads(path.read_text(encoding='utf-8-sig'))
        self.sites = self.config['sites']
        self.numeric_prefixes = {prefix for site in self.sites.values() for prefix in site.get('prefixes', [])}
        self.overrides = {k.casefold(): v for k, v in self.config.get('problem_overrides', {}).items()}
        for name, site in self.sites.items():
            base = site['base_url'].rstrip('/')
            if urlsplit(base).scheme not in ('http', 'https') or not urlsplit(base).netloc:
                raise ValueError(f'oj.json: {name}.base_url 必须是完整的 http(s) 地址')
            site['base_url'] = base

    def site_url(self, site, kind, **values):
        rule = self.sites[site]
        return rule['base_url'] + rule[kind].format(**values)

    def resolve(self, value):
        value = value.strip()
        if not value or value == '#': return ''
        # A portable reference such as soj:contest/185 never embeds a host.
        match = re.fullmatch(r'([a-z][a-z0-9]*):(problem|contest)/([A-Za-z0-9_-]+)', value, re.I)
        if match and match[1].lower() in self.sites:
            return self.site_url(match[1].lower(), match[2], id=match[3])
        for site in self.sites.values():
            for old in site.get('legacy_base_urls', []):
                old = old.rstrip('/')
                if value == old or value.startswith(old + '/') or value.startswith(old + '?'):
                    return site['base_url'] + value[len(old):]
        return value

    def atcoder_parts(self, pid):
        pid = pid.lower()
        if pid.startswith('at_'):
            match = re.fullmatch(r'at_(.+)_([a-z]+[0-9]*)', pid)
            if not match: return None
            slug, task = match.groups()
        else:
            match = re.fullmatch(r'((?:abc|arc|agc)[0-9]+)_?([a-z]+[0-9]*)', pid)
            if match: slug, task = match.groups()
            else:
                match = re.fullmatch(r'(awtf[0-9]+)([a-z][0-9]*)', pid)
                if not match: return None
                slug, task = match.groups()
        contest = self.config.get('atcoder_contest_aliases', {}).get(slug, slug)
        return contest, f'{slug}_{task}'

    def problem(self, pid):
        key = pid.casefold()
        if key in self.overrides: return self.resolve(self.overrides[key])
        match = re.fullmatch(r'cf([0-9]+)([a-z]+[0-9]*)', key)
        if match:
            return self.site_url('codeforces', 'problem', contest=match[1], task=match[2].upper())
        at = self.atcoder_parts(key)
        if at:
            return self.site_url('atcoder', 'problem', contest=at[0], task=at[1])
        match = re.fullmatch(r'hdu([0-9]+)([a-z])', key)
        if match:
            return self.site_url('hdu', 'contest_problem', contest=match[1], id=1001 + ord(match[2]) - ord('a'))
        match = re.fullmatch(r'([a-z]+)([0-9]+)', key)
        if match:
            for name, site in self.sites.items():
                if match[1] in site.get('prefixes', []):
                    return self.site_url(name, 'problem', id=match[2])
        return '#'

    def contest_for_problem(self, pid):
        match = re.fullmatch(r'cf([0-9]+)[a-z]+[0-9]*', pid, re.I)
        if match: return self.site_url('codeforces', 'contest', id=match[1])
        at = self.atcoder_parts(pid)
        if at: return self.site_url('atcoder', 'contest', id=at[0])
        return ''


def strip_comment(line):
    """Only whitespace-prefixed # starts a comment; URL fragments and C# survive."""
    return re.split(r'(?:^|\s+)#', line, maxsplit=1)[0].strip()


def normalize_category(value):
    return {'oi': 'OI', 'ois': 'OIs', 'xcpc': 'XCPC', 'codeforces': 'Codeforces', 'atcoder': 'AtCoder'}.get(value.strip().casefold(), value.strip())
