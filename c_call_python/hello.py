def show(name):   
        #print 'hello ' + name 
        #dict = {'obj':'show',}
        #print(dict)
        name = 'heshuqiang'
        f_pos = 12.25365
        f_sim = 0.9856
        dict = "1, 'persion', 1.5, 1.6"
        #print(str(fpos))
        dict = name + ',' + str(f_pos) + ',' + str(f_sim) + ';'
        print(dict)
        return str(dict)
def objTest(str, para):
    print('-------------------------------------')
    print(para)
    print('-------------------------------------')
    print('--obj test')
    print(str)

class Calc():
    def __init__(self, a, b, sum):
        self.a = a
        self.b = b
        self.sum = sum

    def add(self):
        self.sum = self.a + self.b
        return self.sum

   
def test_hello(name):
    print("hello play phone test...")
    print(name)

    calc = Calc(5, 3, 0)
    sum = calc.add()
    print("************************")
    print(sum)
    return sum