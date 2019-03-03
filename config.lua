testFloat = 1/3
testUint = 65
testString = "Woah!!"
testDouble = 65.78
testInt = -18

function vec2(_x,_y)
  return {x=_x,y=_y}
end

function vec3(_x,_y,_z)
  return {x=_x,y=_y,z=_z}
end

tree = {
  --testVec = {2.44, 456.2};
  testVec = vec3(0.16, 0.2, 12.2);
  stree = {
    number = 42;
  };
};

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
