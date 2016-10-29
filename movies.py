import sys
import pandas

panda = pandas.read_excel("movies.xlsx",index_col=0)
frame = panda.index.get_values()

class passen:
    def __init__(self,movies):
        self.movies = sorted(movies.tolist())
        self.matched_list = []
        self.first = self.movies[0]
        self.matched_list.append(self.first)
        self.starts = self.first[0]
        self.ends = self.first[len(self.first)-1]
        self.go = True

    def next(self):
        try:
            next_word = [word for word in self.movies if word.startswith(self.ends)][0]
            self.starts = next_word[0]
            self.ends = next_word[len(next_word)-1]
            self.movies.remove(next_word)
            return next_word
        except IndexError:
            self.go = False

    def do(self):
        while self.go:
            self.matched_list.append(self.next())
        return self.matched_list


match = passen(frame)
print match.do()
