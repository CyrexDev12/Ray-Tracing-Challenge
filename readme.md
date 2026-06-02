Notes: 

Compile Command 
g++ -std=c++11 main.cpp Matrix.cpp -o program


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


Identifying Hits 
- When rendering a scene we will need to identify which one of the intersections is actually visible from the ray's origin. 
(Some can be behind the ray, and others may be hidden or behind by other objects)
- We call the visible intersection the 'hit' 
(The hit will never be behind the ray's origin) (Since it is effectivley behind the camera), so we can ignore all intersections with negative t values. The hit will always be the intersection with the lowest nonnegative t value. 


Moving the sphere 
When we increase the distance between the sphere and the ray, we can translate the ray away from the sphere, and it is indifferent from
translating the sphere away from the ray. 

Scaling 
- If we want to make our sphere bigger it is just the same as shrinking the distance between the ray and the sphere. 
- It is an inverse relationship. 
- We scale the ray by the inverse of how you were wanting to scale the sphere. 

Rotation 
- If we want to rotate the sphere, you rotate the sphere by the inverse of the rotation you wanted to apply to the sphere. 

To sum up transformations, whatever transformation we want to apply to the sphere, we apply the inverse to the ray. 


