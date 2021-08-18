import random

def create_2D_matrix(height: int, length: int, init=None) -> list:
  """
  Function to create a square matrix
  """
  return [[ init for j in range(0, length) ] for i in range(0, height) ]

def random_populate(matrix: list = None) -> list:
  """
  Populates a matrix with random numbers
  """
  if matrix == None:
    return None

  for row in range(0, len(matrix)):
    for element in range(0, len(matrix[row])):
      matrix[row][element] = random.randint(0, 50)

  return matrix

def pretty_print(matrix: list = None, end: str = '\n'):
  if matrix == None:
    return

  for row in matrix:
    print("[ ", end='')
    for col in row:
      print(f"{col:2} ", end='')

    print("]")

  print(end)

def rotate_clockwise(matrix: list = None) -> list:
  """
  Rotates clockwise the matrix
  """
  if matrix == None:
    return None

  new_matrix = []

  # Iterates through columns from the first to the last
  for col in range(0, len(matrix[0])):
    inn_arr = []
    for index in range(len(matrix)-1, -1, -1):
      inn_arr.append(matrix[index][col])

    new_matrix.append(inn_arr)

  return new_matrix

def rotate_nonclockwise(matrix: list = None) -> list:
  """
  Rotates non-clockwise the matrix
  """
  if matrix == None:
    return None

  new_matrix = []

  # Iterates through columns from the last to the first
  for col in range(len(matrix[0])-1, -1, -1):
    inn_arr = []
    for index in range(0, len(matrix)):
      inn_arr.append(matrix[index][col])

    new_matrix.append(inn_arr)

  return new_matrix

def mirror(matrix: list = None) -> list:
  """
  Mirror the matrix according to the diagonal
  """
  if matrix == None:
    return None

  new_matrix = []

  for col in range(len(matrix[0])-1, -1, -1):
    inn_arr = []
    for row in range(len(matrix)-1, -1, -1):
      inn_arr.append(matrix[row][col])

    new_matrix.append(inn_arr)

  return new_matrix

# Create a matrix
matrix = create_2D_matrix(3, 3)

# Load with significant data
print("Matrix:")
matrix = random_populate(matrix)
pretty_print(matrix)

# Rotate the matrix clockwise
print("90 Rotated:")
matrix = rotate_clockwise(matrix)
pretty_print(matrix)

# Rotate the matrix non-clockwise
print("-90 Rotated:")
matrix = rotate_nonclockwise(matrix)
pretty_print(matrix)

# Mirror the matrix
print("Mirrored:")
matrix = mirror(matrix)
pretty_print(matrix)
