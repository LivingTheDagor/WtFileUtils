class ResizeableList:
    def __init__(self, suggested_size: int, obj_initializer, params):
        self.size = suggested_size
        self.obj_initializer = obj_initializer
        self.list_: list = [obj_initializer(*params) for x in range(suggested_size)]
        self.params = params

    def __getitem__(self, item):
        if isinstance(item, int):
            if item >= self.size:
                self.list_.extend([self.obj_initializer(*self.params) for x in range(self.size, item + 1)])
                self.size = item + 1
            return self.list_[item]
        return None

    def __setitem__(self, key, value):
        if isinstance(key, int):
            not_needed_fuck_you_checker = self[key]  # does a forced resize
            if type(value) is not self.obj_initializer:
                raise TypeError(f"Invalid Object of type {type(value)} when {self.obj_initializer} was needed")
            self.list_[key] = value
            return
        raise IndexError(f"Invalid index type of {type(key)} when int is needed")

    def __iter__(self):
        return iter(self.list_)

    def __len__(self):
        return len(self.list_)
