inspect = require 'inspect'

function fclean() os.execute("make -C .. fclean") end
function make() os.execute("make -C ..") end
function re() fclean() make() end

function listChampions()
	local i, t, popen = 0, {}, io.popen
	for filename in popen('ls -a "'..champions..'" | grep \\.cor'):lines() do
		i = i + 1
		t[i] = champions..filename
	end
	return t
end

function getChampion(nbrChampions)
	math.randomseed(os.time())

	local str = ""
	for i=1, nbrChampions do
		local nbr = math.random(#championsList)
		str = str.." -n "..championsList[nbr]

	end
	return str
end

function catchReturn(line, cnames)
	if line:find("^%d+$") then
		if tonumber(line) ~= 0 then
			file = io.open("log/"..cnames, "w")
			file:write(cnames.."\tError: "..line.."\n")
			file:close()
			table.insert(errorTable, cnames.."\tcatchReturn")
		end
	end
end

function catchWinner(line, cnames)
	local a, b, name = line:find("Winner.+, (.+)$")
	local a, b, err = line:find("Winner.+(%d+), (.+)$")
	if name then print("get Winner : "..name) end
	if err then print("get Winner Zero") end
end

function catch(line, cnames)
	catchReturn(line, cnames)
	catchWinner(line, cnames)
	-- print(line)
end

function concat(champions)
	return corewar..champions.." 2>&1; echo $?"
end

function exec(string, cnames)
	print(string)

	for line in io.popen(string):lines() do
		catch(line, cnames)
	end
end

function dump()
	for i,v in ipairs(errorTable) do
		print(v)
	end
end

re()

corewar = "../corewar"
champions = "../champions/"

championsList = listChampions()

for i,v in ipairs(championsList) do
	errorTable = {}
	a,b, name = v:find(".+/(.+).cor")
	exec(concat(" -n "..v), name)
	dump()
end

