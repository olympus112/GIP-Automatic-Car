component = require("component")
computer = require("computer")
side = require("sides")
robot = component.proxy(component.list("robot")())
inv = component.inventory_controller
geo = component.geolyzer


field = {}
local x,y,d = 2,2,0

function forward()
  if not robot.move(side.front) then return false end
  if d == 0 then
    x = x + 1
  elseif d == 1 then
    y = y + 1
  elseif d == 2 then
    x = x - 1
  elseif d == 3 then
    y = y - 1
  end
  return true
end

function turnLeft() d = (d + 3) % 4; robot.turn(false) end
function turnRight() d = (d + 1) % 4; robot.turn(true) end
function detectLeft() robot.turn(false); local b = robot.detect(3); robot.turn(true); return b end
function detectRight() robot.turn(true); local b = robot.detect(3); robot.turn(false); return b end
function detect() return (robot.detect(side.front)) end

function set(x, y, val)
  if not field[x] then field[x] = {} end
  field[x][y] = val
end
function get(x,y)
  return field[x][y]
end
function getBlock()
  if d == 0 then
    return x+1,y
  elseif d == 1 then
    return x,y+1
  elseif d == 2 then
    return x-1,y
  elseif d == 3 then
    return x,y-1
  end
end
-- EXPLORATION

repeat
  turnRight()
  repeat
    local bx,by = getBlock()
    local bl = detect()
    set(bx,by,bl)
    if bl then turnLeft() end
  until not bl
  forward()
until x == 2 and y == 2
while d ~= 0 do
  turnLeft()
end