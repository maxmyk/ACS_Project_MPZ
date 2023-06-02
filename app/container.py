class Container:
    def __init__(self):
        self.dict = dict()

    def addValue(self, keyHub, keySensor, value):
        values_ls = self.dict.get((keyHub, keySensor), [])
        values_ls.append(value)
        self.dict[(keyHub, keySensor)] = values_ls[-20:] if len(values_ls) > 20 else values_ls

    def getLastValue(self, keyHub, keySensor):
        return self.dict.get((keyHub, keySensor), [None])[-1]

    def getAllValues(self, keyHub, keySensor):
        return self.dict.get((keyHub, keySensor), [None])