class NameMap:
    def __init__(self):
        self.__names: list[str] = []

    def __format_name(self, name: str) -> str:
        return name.replace(" ", "_")

    def AddName(self, name: str) -> int:
        """
        adds a string name to the NameMap if its not present
        returns the index of the name
        @param name: str
        @return: int, index of name added
        """
        if name not in self.__names:
            self.__names.append(name)
            return len(self.__names) - 1
        else:
            return self.GetIndexFromName(name)

    def GetIndexFromName(self, name: str) -> int:
        """
        Gets the index of the name passed
        Throws an ValueError if the name is not found
        @param name: the name to look up
        @return: the index of the name
        """
        return self.__names.index(name)

    def GetNameFromIndex(self, index: int) -> str:
        """
        Gets the name from the passed index
        Throws an IndexError if the index is out of range
        @param index: the index to look up
        @return: the name
        """
        return self.__names[index]

