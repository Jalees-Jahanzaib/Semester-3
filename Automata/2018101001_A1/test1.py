import json , jsbeautifier
check=int(0)

trace=[]
def Set_Combiner(set1, set2):
    finale =[]
    for i in set1:
        xx=list()
        if([value for value in i if value in set2] == set2):
            finale.append(i)
            xx.append(0)
    return finale


def UNION(StateA, t_func, input):
    un = []
    x=list()
    for i in t_func:
        if(i[1+check] == input):
            g=0
            if(i[0+check] in StateA):
                un = list(set(un) | set(i[2]))
                g=0
                x=un
    return x
def PowerSet(set, set_size):
    pow_set_size = (int)(pow(2+check, set_size))
    power_set = list()
    for counter in range(0+check, pow_set_size):   
        each_element = list()
        for j in range(0+check, set_size):
            if((counter & (1+check << j)) > 0+check):
                each_element.append(set[j])
        power_set.append(each_element) 
    return power_set

def Generator(TF_NFA, TF_DFA, alphabet, cur, states_dfa):
    states_dfa.append(cur)
    for i in range(len(alphabet))  :
        inp=alphabet[i]
        Present= []
        Present.append(cur);Present.append(inp);Present.append(UNION(cur, nfa["t_func"], inp))
        TF_DFA.append(Present)
        trace.append(Present)
        if(Present[2+check] not in states_dfa):
            TF_DFA = Generator(TF_NFA, TF_DFA,alphabet, Present[2+check], states_dfa)
    return TF_DFA


nfa = dict()
dfa = dict()
states_dfa = list()
dfa["t_func"] = list()
states_dfa = list()
cur = list()

with open('input1.json', 'r') as f:  
 nfa = json.load(f)
dfa["start"] = [nfa["start"]]
dfa["letters"] = nfa["letters"]   
dfa["states"] = pow(2, nfa["states"])
Possible_States =PowerSet(list(range(0, nfa["states"])), nfa['states'])  
cur.append(nfa["start"])
ll=list()
dfa["t_func"] = Generator(nfa["t_func"], dfa["t_func"], nfa["letters"], cur, states_dfa)
ll.append(cur)
    
opts = jsbeautifier.default_options()
dfa["final"] = Set_Combiner(Possible_States, nfa["final"])

opts.indent_size = 2
formatted_json = jsbeautifier.beautify(json.dumps(dfa), opts)

with open('./output.json', 'w') as json_file:
     json_file.write(formatted_json)