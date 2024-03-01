
"""
Author: Kairu Cyrus

Run in a virtual environment due to problems with my include paths
For us to retain the original triangle, we find the intersection 
of the smaller triangles and the boundary of the original triangle.
The intersections willl be the vertex coordinates of the smaller triangles.
The below code finds the intersections staring from the smallest (nth level) converging towards the larger triangle
Ultimately, we converge to the verices of the original triangle
"""

#function for getting the midpoints of the edges of the triangles, given starting and ending points
def midpoint(p1, p2):
    x = (p1[0] + p2[0]) / 2
    y = (p1[1] + p2[1]) / 2
    return (x, y)

def sierpinski_triangle(vertices, level):
    if level == 0: #the level defines the nummber of recursions we take 
        #or the extent to which we divide the triangle
        return [vertices]
    
    v1, v2, v3 = vertices
    
    # Calculate midpoints
    midpoints = [midpoint(v1, v2), midpoint(v2, v3), midpoint(v3, v1)]
    
    # Create smaller triangles
    smaller_triangles = [
        sierpinski_triangle([vertices[i], midpoints[i], midpoints[(i + 1) % 3]], level - 1)
        for i in range(3)
    ]
    
    return smaller_triangles

# Defining the initial triangle vertices
initial_triangle = [(0, 0), (10, 0), (5, 8.66)]  #  vertices of an equilateral triangle

# Generate Sierpinski triangles
sierpinski_triangles = sierpinski_triangle(initial_triangle, level=3)

# Printing the vertex coordinates of the smaller triangles
def print_triangles(triangles, level=0):
    for i, triangle in enumerate(triangles):
        if isinstance(triangle[0], tuple):  # Checking if this is the leaf node
            print(f"Level {level}, Triangle xx:")
            for vertex in triangle:
                print(vertex)
        else:
            print_triangles(triangle, level + 1)

print_triangles(sierpinski_triangles)
