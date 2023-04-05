class Container:
    def __init__(self):
        self.dict = dict()

    def addValue(self, key, value):
        values_ls = self.dict.get(key, [])
        values_ls.append(value)
        self.dict[key] = values_ls[-10:] if len(values_ls) > 10 else values_ls

    def getLastValue(self, key):
        return self.dict.get(key, [None])[-1]

    def getAllValues(self, key):
        return self.dict.get(key, [None])