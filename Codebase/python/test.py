import sys


def detect_note_in_png(score_path):
    result = score_path + " zhang"
    file = open("file.txt", "w")
    file.write(result)
    file.close()

score_path = sys.argv[1]
detect_note_in_png(score_path)
