import abc


class WriteStream:
    def __init__(self, writepath=None):
        self.writepath = writepath
        self.buffer = []

    def write(self, data):
        if self.writepath is None:
            print(data)
        else:
            self.buffer.append(data)

    def flush(self):
        if self.writepath is not None:
            with open(self.writepath, "w") as f:
                for data in self.buffer:
                    f.write(data)
                    f.write("\n")
