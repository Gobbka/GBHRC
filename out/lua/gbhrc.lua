local screen_gui = GUI.new();
local button = Instance.new("Button");
local panel = Instance.new("Panel");

screen_gui:add_child(panel);

panel.Color = Color3.new(51,51,51);
panel.Size = Float2.new(300,600);

button.Parent = panel;
button.Text   = "nigger";
button.Color  = Color3.new(1,3,228);
button.Size   = Float2.new(228,30);

-- print( Color3.new(1,3,228) );
--print();--