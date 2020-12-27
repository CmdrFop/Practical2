groups = ['0', '1', '2', '3']
elements = groups
group = '0123'
cost = [3, -2, 6, -3]
max_divisions = 2

def recursion_solution(group, cost, max_divisions, elements):
    # If we meet the base case we return the cost for this single item
    if len(group) == 1:
        return cost[int(group)], [group], 1

    # Create 2 sub_groups from the supe group in such a way all possible groups are covered
    rec_group1 = group[:-1]
    rec_group2 = group[1:]
    elements1 = elements[:-1]
    elements2 = elements[1:]

    # Recursion, we split up the group unitl it reaches it atoms (base case) , on the way we compute the best cost
    # and combination of groups
    cost_group1, group1, division1 = recursion_solution(rec_group1, cost, max_divisions, elements1)
    cost_group2, group2, division2 = recursion_solution(rec_group2, cost, max_divisions, elements2)

    # If groups overlap add the best one
    if len(list(set(elements1) & set(elements2))) > 0:
        if cost_group1 < cost_group2:
            alternative_cost = cost_group1 + cost[int(elements2[-1])]
            right_groups = group1 + [elements2[-1]]
            division = division1
        else:
            alternative_cost = cost_group2 + cost[int(elements1[0])]
            right_groups = group2 + [elements[0]]
            division = division2
    # If they do not overlap combine the cost of these 2 groups
    else:
        alternative_cost = cost_group1 + cost_group2
        right_groups = group1 + group2
        division =  division1 + division2

    # Compare the cost of the sub group calculated in the recursion function to the cost of recomputing the combined
    # cost
    
    if round(alternative_cost) > alternative_cost and (division + 1 < max_divisions):
        return alternative_cost, right_groups, division + 1
    # if the new computed score is better remove the sub groups and use the larger group
    else:
        return round(alternative_cost), [group], 1
    
smallest_cost, best_group, divisions = recursion_solution(group, cost, max_divisions, elements)

print(smallest_cost)
print(best_group)
print(divisions)