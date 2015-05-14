inspect = require 'inspect'

function fclean() os.execute("make -C .. fclean") end
function make() os.execute("make -C ..") end
function re() fclean() make() end

function listChampions(ext)
	local i, t, popen = 0, {}, io.popen
	for filename in popen('ls '..championsPath..' | grep \\\\.'..ext):lines() do
		i = i + 1
		t[i] = championsPath..filename
	end
	return t
end

function getChampion(nbrChampion)
	math.randomseed(os.time())

	local str = ""
	for i=1, nbrChampion do
		local nbr = math.random(#championsList)
		str = str.." -n "..championsList[nbr]

	end
	return str
end

function catchReturn(line, cnames)
	if line:find("^%d+$") then
		if tonumber(line) ~= 0 then
			file = io.open("log/"..cnames, "a")
			file:write(cnames.."\tError: "..line.."\n")
			file:close()
			table.insert(errorTable, cnames.."\tcatchReturn")
		end
	end
end

function catchWinner(line, cnames)
	local a, b, name = line:find("Winner.+, (.+)$")
	if name then print("get Winner : "..name) end
end

function catch(line, cnames)
	catchReturn(line, cnames)
	catchWinner(line, cnames)
	-- print(line)
end

function concat(champions)
	return corewar..championsPath.." 2>&1; echo $?"
end

function exec(string, cnames)
	print(string)

	file = io.open("log/"..cnames, "w");
	file:close()
	for line in io.popen(string):lines() do
		catch(line, cnames)
	end
end

function dump()
	for i,v in ipairs(errorTable) do
		print(v)
	end
end

math.randomseed(os.time())

zaz_asm = "~/Desktop/corewar/asm"
corewar = "../corewar"
championsPath = "../champions/"


nbrChampion = 2
championsList = listChampions("s")

for i,v in ipairs(championsList) do
	-- local un, deux, champ = v:find("(.+/champions/.+s)")
	print(zaz_asm.." "..v)
	for line in io.popen(zaz_asm.." "..v):lines() do
		local tmp1, tmp2, match = line:find("(output)")
		if match then print("Ok")
		else print(line) end
	end
end

championsList = listChampions("cor")

for i,v in ipairs(championsList) do
	a,b, name = v:find(".+/(.+).cor")
	for i=1,nbrChampion - 1 do
		local rand = math.random(#championsList)
		_,__, name2 = championsList[rand]:find(".+/(.+).cor")
		name = name2..":"..name
		v = v..championsList[rand]
	end
	-- print(rand, championsList[rand])
	errorTable = {}
	exec(corewar.." "..string.gsub(v, " ?("..championsPath..")", " -n %1"), name)
end

