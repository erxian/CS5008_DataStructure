# Exercises

Discuss and answer the following questions (Make sure to elaborate and justify your responses):

1. How good is the provided hash function--are we really getting constant time operations with our hashmap?
2. What is one other way you could implement the hash function? Anything creative is acceptable in this answer.
3. If I have to resize the hashmap to add more buckets, what is th Big-O complexity?
4. What is 'open addressing' in regards to hash maps and hash tables?

## Answers:

1. tolerable but not the best practice. We're getting constant time when insert, but we got O(n) when getValue(), hasKey() and update() and remove() under worsest situation. And chaining hash has additional memory cost to store the structure of linked-lists.
2. using two Hash function, one used for find the buckets and the other one used to find the value.
3. O(n)
4. open addressing is a method for handling collisions. In Open Addressing, all elements are stored in the hash table itself.


