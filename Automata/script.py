import json


def generatePowerSet(set, set_size):
    pow_set_size = (int)(pow(2, set_size))
    power_set = list()
    for counter in range(0, pow_set_size):    # Run the counter from 000..0 to 111..1
        each_element = list()
        for j in range(0, set_size):
            # Check if jth bit in the counter is set and then append it to the set
            if((counter & (1 << j)) > 0):
                each_element.append(set[j])
        power_set.append(each_element)  # append the set to the power set
    return power_set


def final_set_generator(set1, set2):
    # find all those elements in set1 containing all the elements in set2
    finale = list()
    for i in set1:
        if([value for value in i if value in set2] == set2):
            finale.append(i)
    return finale


def op_for(initial_state, t_func, input):
    # finds the union of the outputs of each element in initial_state for initial_state given input
    ans = list()
    for i in t_func:
        if(i[1] == input):
            if(i[0] in initial_state):
                ans = list(set(ans) | set(i[2]))
    return ans


def make_clean(t_func, reachable):
    # Removes those states with no transitions from the t_function
    # Also removes un-reachable states
    print(reachable)
    final_lis = []
    for item in t_func:
        if item[0] != [] and item[2] != []:
            if(item[0] in reachable):
                print(item)
                final_lis.append(item)
    return final_lis


def generate_t_func_dfa(t_func_nfa, t_func_dfa, alphabet, cur, states_dfa):
    # repeat from here
    states_dfa.append(cur)
    # then for append all the transitions from start to the dfa's t_func for all input alphabets
    for inp in alphabet:
        p = list()
        p.append(cur)  # starting state
        p.append(inp)  # input character
        p.append(op_for(cur, nfa["t_func"], inp))  # next state
        t_func_dfa.append(p)
        # repeat for each of the next state of the transition function
        if(p[2] not in states_dfa):
            t_func_dfa = generate_t_func_dfa(
                t_func_nfa, t_func_dfa,
                alphabet, p[2], states_dfa)
    return t_func_dfa


if __name__ == "__main__":
    nfa = dict()
    with open('input1.json', 'r') as f:  # load the NFA from the file
        nfa = json.load(f)
    # print(nfa)
    dfa = dict()
    dfa["states"] = pow(2, nfa["states"])
    dfa["letters"] = nfa["letters"]
    dfa["start"] = [nfa["start"]]
    all_states_dfa = generatePowerSet(
        list(range(0, nfa["states"])), nfa['states'])
    dfa["t_func"] = list()
    # cur = nfa["start"]

    # reading the algorithm, this is what I understood
    # first make a new state list for the dfa
    states_dfa = list()
    cur = list()
    cur.append(nfa["start"])
    # append start of nfa to it
    dfa["t_func"] = generate_t_func_dfa(
        nfa["t_func"], dfa["t_func"], nfa["letters"], cur, states_dfa)

 

    dfa["final"] = final_set_generator(all_states_dfa, nfa["final"])
    # print(dfa)
    with open('output.json', 'w') as outfile:
        json.dump(dfa, outfile, indent=None)
