import re

def msg(s):
    print('\033[1m\033[91m' + s + '\033[0m\033[0m')

f_out = "./workdir/a.out"
f_json = "./workdir/a.json"
pattern1 = re.compile(r"Error type (\d+) at Line (\d+): .*\.")
pattern2 = re.compile(r"Error Type (\d+) at Line (\d+):. *")
failure = False

json = open(f_json)
out = open(f_out)
real = {}
# check if they are valid errors 
our_count = 0
real_count = 0
error_line_num = 0
vis = {}
for line in out.readlines():
    our_count += 1
    m = pattern1.match(line)
    if(line.strip() == ""):
        breaks
    if(not m):
        msg(line)
        msg("Wrong output format!")
        exit(1);
    x, y = m.groups();
    pos = (int(x), int(y))
    real[pos] = True
    if y not in vis:
        vis[y] = True
        error_line_num+=1

for line in json.readlines():
    real_count += 1 
    m = pattern2.match(line)
    x, y = m.groups()
    pos = (int(x), int(y))
    if pos not in real.keys():
        # msg("miss error %d at line %d." % (pos))
        print("miss error %d at line %d." % (pos))
        failure = True  

if failure :
    exit(1)


if error_line_num >  real_count :
    for key in real:
        print(key)

    print('--')
    for key in vis:
        print(key)

    exit(1)

exit(0)
