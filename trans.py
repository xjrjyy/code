'''
URL 转文件名，支持从剪贴板读取。

TODO: Luogu AT RemoteJudge
'''

READ_FROM_CLIP = True

# TODO: filename to url

from enum import Enum
from typing import Optional
import re
import pyperclip

RE_CF_PID = r'([a-zA-Z][1-9]?)'
RE_LOJ_URL = re.compile(r'.*loj\.ac/p/(\d+)')
RE_UOJ_URL = re.compile(r'.*uoj\.ac/problem/(\d+)')
RE_LUOGU_URL = re.compile(r'.*luogu\.com\.cn/problem/([a-zA-Z]{1,3}[0-9a-zA-Z_]+)')
RE_CF_URL = re.compile(r'.*codeforces\.com/problemset/problem/(\d+)/' + RE_CF_PID)
RE_CF_GYM_URL = re.compile(r'.*codeforces\.com/gym/(\d+)/problem/' + RE_CF_PID)
RE_AT_URL = re.compile(r'.*atcoder\.jp/contests/a[brg]c\d{3}/tasks/(a[brg]c\d{3})_([1-9a-zA-Z])')

RE_LUOGU_P_PROBLEM = re.compile(r'P(\d{4,})')
RE_LUOGU_REMOTE_CF_PROBLEM = re.compile(r'CF(\d+)' + RE_CF_PID)
RE_LUOGU_REMOTE_AT_PROBLEM = re.compile(r'AT_(a[brg]c\d{3})_([1-9a-zA-Z])')

class OJType(Enum):
    Loj = 'loj'
    Uoj = 'uoj'
    Luogu = 'luogu'
    Codeforces = 'cf'
    CodeforcesGym = 'cf_gym'
    Atcoder = 'at'

    def __str__(self) -> str:
        return self.value

class ProblemInfo:
    def __init__(self, oj: OJType, id: str, name: Optional[str]=None, contest: Optional[str]=None) -> None:
        # TODO: type
        self.oj = oj
        self.id = id.lower()
        self.name = name.lower() if name else None
        self.contest = contest.lower() if contest else None
    
    def __str__(self) -> str:
        msg = f'{self.oj}: '
        if self.contest: msg += f'{self.contest}'
        msg += f'{self.id}'
        if self.name: msg += f'({self.name})'
        return msg
    
    def to_filename(self) -> Optional[str]:
        if self.oj == OJType.Loj:
            return f'{str(self.oj)}_p{self.id}'
        if self.oj == OJType.Uoj:
            return f'{str(self.oj)}_p{self.id}'
        if self.oj == OJType.Luogu:
            return f'{str(self.oj)}_{self.id}'
        if self.oj == OJType.Codeforces:
            return f'{str(self.oj)}_{self.contest}_{self.id}'
        if self.oj == OJType.CodeforcesGym:
            return f'{str(self.oj)}_{self.contest}_{self.id}'
        if self.oj == OJType.Atcoder:
            return f'{str(self.oj)}_{self.contest}_{self.id}'
        return None

def parse_loj_pid(pid: str) -> Optional[ProblemInfo]:
    return ProblemInfo(OJType.Loj, pid)

def parse_uoj_pid(pid: str) -> Optional[ProblemInfo]:
    return ProblemInfo(OJType.Uoj, pid)

def parse_luogu_pid(pid: str) -> Optional[ProblemInfo]:
    if RE_LUOGU_P_PROBLEM.match(pid):
        return ProblemInfo(OJType.Luogu, pid)
    if RE_LUOGU_REMOTE_CF_PROBLEM.match(pid):
        contest, pid = RE_LUOGU_REMOTE_CF_PROBLEM.match(pid).groups()
        return parse_cf_pid(contest, pid)
    if RE_LUOGU_REMOTE_AT_PROBLEM.match(pid):
        contest, pid = RE_LUOGU_REMOTE_AT_PROBLEM.match(pid).groups()
        return parse_at_pid(contest, pid)
    return None

def parse_cf_pid(contest: str, pid: str) -> Optional[ProblemInfo]:
    return ProblemInfo(OJType.Codeforces, pid, contest=contest)

def parse_cf_gym_pid(contest: str, pid: str) -> Optional[ProblemInfo]:
    return ProblemInfo(OJType.CodeforcesGym, pid, contest=contest)

def parse_at_pid(contest: str, pid: str) -> Optional[ProblemInfo]:
    raw_id = pid if pid.isalpha() else chr(int(pid) - 1 + ord('a')) # arc001_1
    return ProblemInfo(OJType.Atcoder, raw_id, contest=contest)

def parse_url_info(url: str) -> Optional[ProblemInfo]:
    # Loj
    if RE_LOJ_URL.match(url):
        pid, = RE_LOJ_URL.match(url).groups()
        return parse_loj_pid(pid)
    # Uoj
    if RE_UOJ_URL.match(url):
        pid, = RE_UOJ_URL.match(url).groups()
        return parse_uoj_pid(pid)
    # Luogu
    if RE_LUOGU_URL.match(url):
        pid, = RE_LUOGU_URL.match(url).groups()
        return parse_luogu_pid(pid)
    # Codeforces
    if RE_CF_URL.match(url):
        contest, pid = RE_CF_URL.match(url).groups()
        return parse_cf_pid(contest, pid)
    # Codeforces Gym
    if RE_CF_GYM_URL.match(url):
        contest, pid = RE_CF_GYM_URL.match(url).groups()
        return parse_cf_gym_pid(contest, pid)
    # Atcoder
    if RE_AT_URL.match(url):
        contest, pid = RE_AT_URL.match(url).groups()
        return parse_at_pid(contest, pid)
    return None

def url_to_filename(url: str) -> Optional[str]:
    info = parse_url_info(url)
    if not info: return None
    return info.to_filename()

def test():
    # TODO: failed tests
    urls = {
        'https://loj.ac/p/1': 'loj_p1',
        'https://uoj.ac/problem/1': 'uoj_p1',
        'https://www.luogu.com.cn/problem/P1001': 'luogu_p1001',
        'https://codeforces.com/problemset/problem/1/A': 'cf_1_a',
        'https://codeforces.com/problemset/problem/1450/C2': 'cf_1450_c2',
        'https://codeforces.com/gym/100001/problem/A': 'cf_gym_100001_a',
        'https://atcoder.jp/contests/arc001/tasks/arc001_1': 'at_arc001_a',
        'https://atcoder.jp/contests/arc058/tasks/arc058_a': 'at_arc058_a',
        # Luogu RemoteJudge
        'https://www.luogu.com.cn/problem/CF1A': 'cf_1_a',
        'https://www.luogu.com.cn/problem/CF1450C2': 'cf_1450_c2',
        'https://www.luogu.com.cn/problem/AT_arc058_a': 'at_arc058_a',
    }
    for (url, filename) in urls.items():
        info = parse_url_info(url)
        url_filename = url_to_filename(url)
        print(f'url: info={info} filename={url_filename}')
        assert(filename == url_filename)

if __name__ == '__main__':
    if READ_FROM_CLIP:
        url = pyperclip.paste().strip()
        filename = url_to_filename(url)
        if filename: print(f'From Clip: {filename}')

    print('Input Problem Url(s):')
    while True:
        url = input().strip()
        print(url_to_filename(url))
