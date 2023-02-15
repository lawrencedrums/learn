import random
import sys
import webbrowser


"""
!!!FREE MICROSOFT REWARD POINTS!!!

Take one optional arg of number between 1 and 100
Open that amount of tabs in Edge, searching a random number
in Bing in each of those tabs...
"""
def main(tabs):
    if not tabs:  # if no args...
        tabs = 50 # TODO: how to better handle optional args

    # TODO: use correct path base on OS
    win_path = "C:\Program File (x86)\Microsoft\Edge\Application\msedge.exe"
    mac_path = ""
    linux_path = ""

    search_string = "https://www.bing.com/search?q="
    reward_url = "https://rewards.bing.com/redeem/"

    webbrowser.register('edge', None, webbrowser.BackgroundBrowser(win_path))

    for _ in range(tabs):
        rand_num = random.randint(0, 50000)
        webbrowser.get('edge').open(f"{search_string}{rand_num}")

    webbrowser.get('edge').open_new(reward_url)

def validate(argv):
    if len(argv) > 2:
        return False
    if len(argv) == 2 and not argv[1].isdigit():
        return False

    return True

def arg2int(argv):
    return int(argv[1]) if len(argv) == 2 else None


if __name__ == "__main__":
    usage = """
            Usage:
                gimme_points.py n (optional)
                : 1 <= n <= 100
            """ 
    validated = validate(sys.argv)

    if not validated:
        print(usage)
    else:
        tabs = arg2int(sys.argv)
        main(tabs)

