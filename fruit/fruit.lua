-- fruit.lua

-- Defining object/class
local Fruit = {}

-- Overriding the metamethod of the metatable for the Fruit object since it's
-- not a normal table anymore.
Fruit.__index = Fruit

-- Basically a constructor
function Fruit.create(name)
   -- Creates the metatable
   local self = setmetatable({}, Fruit)

   -- Initiating the value and returning the new instance
   self.name = name
   return self
end

-- Defining a setter method for the fruit's name
function Fruit:set_name(name)
   self.name = name
end

-- Defining the string method with the : that implicitly puts a self arg as
-- first argument.
function Fruit:get_name()
   -- Returning the name
   return '"'..self.name..'"'
end

-- Returing the class
return Fruit
