list1, list2, pairs = [], [], []

# Generate lists
with open("./input.txt") as f:
    for x in f:
        pairs = x.split("   ")
        list1.append(pairs[0].strip())
        list2.append(pairs[1].strip())

num_appearances = {}
similarity = 0


# Count how many times a given value appears in the second list
def calc_appearances(x):
    return list2.count(x)


# If the similarity has not been calculated then we calculate it, then we sum the Similarity Score
for x in list1:
    if num_appearances.get(x) is None:
        num_appearances[x] = calc_appearances(x)
    similarity += int(x) * num_appearances[x]


# Sort them
# We have to do part 2 first since we are destroying the lists
list1.sort()
list2.sort()

distance = 0


# Absolute Value to find distance
def calc_distance(left, right):
    return abs(int(left) - int(right))


# Sum Distance
while list1 != []:
    distance += calc_distance(left=list1.pop(0), right=list2.pop(0))


print(f"Distance: {distance}")  # 1765812
print(f"Similarity Score: {similarity}")  # 20520794
