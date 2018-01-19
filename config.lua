testFloat = 1/3
testUint = 65
testString = "Woah!"
testDouble = 65.78
testInt = -18

--[[
function DegToRad(n)
  return math.rad(n)
end

function Vector2(x, y)
  return x, y
end

-- Attacker sub-tree
Attacker = {
  aim_width = DegToRad(1.4);
  drive_offset = Vector2(0.1, 0.2);
};

if RobotID == 1 then
  drive_offset = Vector2(0.02, 0.03);
end
--]]
