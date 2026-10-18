"""Run with: python _check.py. Temporary fixtures never touch the real archive."""
import json
import tempfile
import unittest
from pathlib import Path
import _run
from _links import LinkResolver, strip_comment


class RegressionChecks(unittest.TestCase):
    def test_oj_rules(self):
        links = LinkResolver()
        cases = {
            'cf2206d': 'https://codeforces.com/problemset/problem/2206/D',
            'cf2152h2': 'https://codeforces.com/problemset/problem/2152/H2',
            'AT_fps_24_n': 'https://atcoder.jp/contests/fps-24/tasks/fps_24_n',
            'AT_jsc2023_final_f': 'https://atcoder.jp/contests/jsc2023-final/tasks/jsc2023_final_f',
            'AT_xmascon20_f': 'https://atcoder.jp/contests/xmascon20/tasks/xmascon20_f',
            'awtf2025c': 'https://atcoder.jp/contests/awtf2025algo/tasks/awtf2025_c',
            'loj180': 'https://loj.ac/p/180',
            'zr2138': 'https://zhengruioi.com/problem/2138',
            'hdu1236a': 'https://acm.hdu.edu.cn/contest/problem?cid=1236&pid=1001',
            'hdu1238k': 'https://acm.hdu.edu.cn/contest/problem?cid=1238&pid=1011',
        }
        self.assertEqual(links.contest_for_problem('cf2152h2'), 'https://codeforces.com/contest/2152')
        for pid, url in cases.items():
            with self.subTest(pid=pid): self.assertEqual(links.problem(pid), url)

    def test_host_changes(self):
        config = json.loads(Path(__file__).with_name('oj.json').read_text())
        config['sites']['soj']['base_url'] = 'https://example.org/new-soj'
        config['sites']['zr']['base_url'] = 'https://example.org/new-zr'
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / 'oj.json'
            path.write_text(json.dumps(config))
            links = LinkResolver(path)
            self.assertEqual(links.problem('soj2500'), 'https://example.org/new-soj/problem/2500')
            self.assertEqual(links.resolve('soj:contest/185'), 'https://example.org/new-soj/contest/185')
            self.assertEqual(links.resolve('http://121.196.149.251:8080/problem/2500'), 'https://example.org/new-soj/problem/2500')
            self.assertEqual(links.resolve('https://zhengruioi.com/problem/2138'), 'https://example.org/new-zr/problem/2138')

    def test_comments(self):
        self.assertEqual(strip_comment('https://example.org/#part'), 'https://example.org/#part')
        self.assertEqual(strip_comment('C# graph 3000 # note'), 'C# graph 3000')
        self.assertEqual(strip_comment('#note'), '')

    def test_grouping_and_categories(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            data = root / 'data'; data.mkdir()
            contests = root / 'contest'; contests.mkdir()
            for pid in ('zr2138', 'zr3508', 'qoj100'):
                (data / (pid + '.cpp')).write_text('int main(){}')
            (contests / '1.conf').write_text('test\noi\n\nA qoj100\n')
            groups = _run.scan_and_group_files(data)
            self.assertIn('zr2138', groups)
            self.assertIn('zr3508', groups)
            info = _run.apply_categories_and_links(groups, data, contests)
            self.assertIn('test', info['OI'])
            self.assertEqual(groups['qoj100'].appearances[0][0], 'OI')
            _run.apply_categories_and_links(groups, data, contests)
            self.assertEqual(len(groups['qoj100'].versions['Normal'].appearances), 1)

    def test_link_only_contest_tasks(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp); data = root / 'data'; contests = root / 'contest'
            data.mkdir(); contests.mkdir()
            (data / 'qoj1.cpp').write_text('int main(){}')
            (contests / '1.conf').write_text('test\nXCPC\nhttps://qoj.ac/contest/1\nA qoj1\nB qoj2\n')
            groups = _run.scan_and_group_files(data)
            info = _run.apply_categories_and_links(groups, data, contests)
            self.assertEqual(groups['qoj2'].versions['Normal'].link, 'https://qoj.ac/problem/2')
            self.assertTrue(all(v is None for v in groups['qoj2'].versions['Normal'].files.values()))
            matrix = _run.build_matrix_table({'test': list(groups.values())}, info['XCPC'], 'data')
            self.assertNotIn('https://qoj.ac/problem/2', matrix)
            self.assertNotIn('>B</', matrix)
            self.assertIn('(1 题)', matrix)
            self.assertNotIn('已归档', matrix)
            self.assertNotIn('共 2 题', matrix)
            soj = _run.build_matrix_table({'SOJ Test Round 74': list(groups.values())}, {}, 'data')
            self.assertNotIn('https://qoj.ac/problem/2', soj)
            self.assertNotIn('<th style="width: 38.5%;">B</th>', soj)
            self.assertNotIn('>B</', soj)

    def test_completed_contest_configs(self):
        root = Path(__file__).parent
        counts = {'0003':12,'0006':12,'0007':9,'0008':11,'0011':15,'0012':13,'0015':13,'0017':15,'0018':12,'0019':13,'0020':11,'0022':13,'0026':13,'0029':13,'0030':13}
        for cid, count in counts.items():
            rows = (root / 'contest' / (cid + '.conf')).read_text().splitlines()[3:]
            labels = [line.split()[0] for line in rows if line.strip() and line.split()[0].isalpha() and len(line.split()) == 2]
            self.assertEqual(labels, [chr(65+i) for i in range(count)], cid)
        self.assertIn('K qoj6524', (root / 'contest/0030.conf').read_text())
        self.assertIn('cid=2411', (root / 'contest/0001.conf').read_text())
        self.assertIn('cid=2427', (root / 'contest/0049.conf').read_text())

    def test_read_only_list_scan(self):
        with tempfile.TemporaryDirectory() as tmp:
            file = Path(tmp) / 'list.conf'
            file.write_text('3\nCF2152H2 # note\nAT_fps_24_n\n')
            before = file.read_bytes()
            result = _run.scan_problem_lists(tmp, {})
            self.assertEqual(file.read_bytes(), before)
            self.assertEqual(result['list']['priority'], 3)
            self.assertIn('/2152/H2', result['list']['versions'][0].link)

    def test_organizer_no_run_does_not_prompt(self):
        import contextlib
        import io
        from unittest.mock import patch
        from _upd import FileOrganizer
        organizer = FileOrganizer()
        organizer.check_directories = lambda: True
        organizer.scan_and_process = lambda: True
        organizer.show_stats = lambda: None
        with patch('builtins.input', side_effect=AssertionError('unexpected prompt')), patch.object(organizer, '_run_py_script', side_effect=AssertionError('unexpected build')), contextlib.redirect_stdout(io.StringIO()):
            organizer._run(skip_clean=True, no_run=True)

    def test_code_link_location(self):
        version = _run.ProblemVersion('Normal', '测试 #1')
        version.files['cpp'] = '测试 #1.cpp'
        href = ''.join(_run.render_file_links(version, '../data', '../'))
        self.assertIn('../data/code/', href)
        self.assertIn('%23', href)
        self.assertIn('.cpp.html', href)


if __name__ == '__main__':
    unittest.main()
