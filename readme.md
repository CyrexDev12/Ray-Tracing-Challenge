Notes: 


- Tuple: A point like (-4, 4, 3)
(x,y,z,w)
For a point in 3D space, you typically use w = 1 → (x, y, z, 1)
For a direction/vector, you use w = 0 → (x, y, z, 0)

W = 1 -> Point 
W = 0 -> Vector 



Matrix Implementation 
Using 2D vector dynamic arrays

Matrix Class includes:
vector<vector<double>>
rows
cols

and all of the needed operations 

Matrix Transformations 

Translation, Scaling, Rotation, Shearing can all be represented as matricies 