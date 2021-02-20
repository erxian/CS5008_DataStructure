# Exercises

Discuss and answer the following questions (Make sure to elaborate and justify your responses):

1. How good is the provided hash function--are we really getting constant time operations with our hashmap?
2. What is one other way you could implement the hash function? Anything creative is acceptable in this answer.
3. If I have to resize the hashmap to add more buckets, what is th Big-O complexity?
4. What is 'open addressing' in regards to hash maps and hash tables?

## Answers:

1. tolerable but not the best practice. In real world, we need avoid collision as possible, making kv pairs evenly distributed in the hash table. if we have non-prime buckets capacity, it could entails heavily collisons since the highest common factor of strlen(key) and numberOfBuckets is not 1. We're getting constant time when insert, but will have a worst-case access time of O(n) when getValue(), hasKey() and update() and remove(). 
2. It's better to using an universal hashing function, HASHa,b(key) = ((a*key + b) mod p) mod m, p is a large enough prime number so that every possible keyword key falls within the range of 0 to p-1. m is the number of buckets in the hash table. The range of a, b are a∈{1,2,3,...,p-1}, b∈{0,1,2,...,p-1}.
3.  O(n)
4.  Open addressing is another method for handling collisions instead of using chaining. In Open Addressing, all elements are stored in the hash table itself. There are 3 types of openning address: Linear Probing, Quadratic Probing and Double Hashing. 


