-- menu.lua

local M = {}

M.__index = M

local function getch()
   -- Entering raw mode to read 1 char
   os.execute('stty cbreak')
   os.execute('stty -echo')
   local key = io.stdin:read(1)
   os.execute('stty echo')
   os.execute('stty -cbreak')

   -- Returing the key
   return key
end

function M.createMenu(list)
   local list_size = #list
   local curr_pos = 0
   local input

      -- Printing the list
      for index, value in ipairs(list) do
         io.write(index..') '..value:get_name()..'\n')
      end

      -- Flushing the output and moving the cursor to the first position
      io.write('\27['..list_size..'A')
      io.flush()

   repeat
      -- Asking the input
      input = getch()

      -- Checking th movement
      if input == 'j' then
         if curr_pos == list_size-1 then
            -- Resetting the cursor to the first item
            io.write('\27['..(list_size-1)..'A')
            curr_pos = 0
         else
            -- Moving down
            io.write('\27[1B')
            curr_pos = curr_pos + 1
         end
      elseif input == 'k' then
         if curr_pos == 0 then
            -- Bringing the cursor to the last position
            io.write('\27['..(list_size-1)..'B')
            curr_pos = list_size - 1
         else
            -- Moving up
            io.write('\27[1A')
            curr_pos = curr_pos - 1
         end
      end

      io.flush()
   until input == 'q' or input == '\n'

   -- Positioning the cursor
   print('\27['..(list_size-curr_pos)..'B')

   return list[curr_pos+1]:get_name()
end

-- Returning the module
return M
