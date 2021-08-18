--  first.lua

-- Defining a fruit generator
local fruit = require('fruit')

-- This function will generate `size` fruits, all of them saved in a array of
-- objects `Fruit`
local function gen_fruits(generator, size)
   if generator == nil then return false end
   if size <= 0 then size = 5 end

   -- Defining the table
   local fruits = {}

   -- Creating them by asking the name to the user
   -- (yes starting form 1 'cause lua)
   print('[@] Insert '..size..' different fruits:')
   for i=1, size do
      -- Reading the fruit's name from standard input
      io.write(i..': => ')
      io.flush()
      fruits[i] = fruit.create(io.stdin:read())
   end

   -- Returning the table
   return fruits
end

-- This function will just prints the fruits' name
local function wrt_fruits(fruits)
   -- Checking the table
   if fruits == false then return false end

   -- Printing the fruits' name
   print('[@] Fruits inserted:')
   for index, value in ipairs(fruits) do
      print('['..index..'] => '..value:get_name())
   end
end

-- Unit test
local fruits_table = gen_fruits(fruit, 3)
wrt_fruits(fruits_table)

-- Asking for a menu generator
local menu = require('menu')
print('[@] Choose a fruite:')
print(menu.createMenu(fruits_table))
