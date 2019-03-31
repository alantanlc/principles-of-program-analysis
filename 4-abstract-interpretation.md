### 4 Abstract Interpretation

The purpose of this chapter is to convey some of the essential ideas of Abstract Interpretation. We shall mainly do so in a programming language independent way and thus focus on the design of the property spaces, the functions and computations upon them, and the relationships between them.

We first formulate a notion of correctness for a restricted class of analyses as this will allow us to motivate better some of the key definitions in the development. Then we cover the widening and narrowing techniques that can be used to obtain approximations of the least fixed point and for limiting the number of computation steps needed. Next we consider Galois connections and Galois insertions that allow a costly space of properties to be replaced with one that is less costly. Galois connections can be constructed in a systematic way and can be used to induce one specification of an analysis from another.


### 4.3 Galois Connections

Sometimes calculations on a complete lattice L may be too costly or even uncomputable and this may motivate replacing L by a simpler lattice M. An example is when L is the powerset of integers and M is a lattice of intervals. So rather than performing the analysis p |- l1 |> l2 in L, the idea will be to find a description of the elements of L in M and to perform the analysis p |- m1 |> m2 in M. To express the relationship between L and M it is customary to use an abstraction function...
