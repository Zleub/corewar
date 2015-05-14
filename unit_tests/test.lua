inspect = require 'inspect'

function fclean() os.execute("make -C .. fclean") end
function make() os.execute("make -C ..") end
function re() fclean() make() end

function listChampions(ext)
	local i, t, popen = 0, {}, io.popen
	for filename in popen('ruby combination.rb | grep \\\\.'..ext):lines() do
		i = i + 1
		t[i] = filename
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
	return corewar..champions.." 2>&1; echo $?"
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

zaz_asm = "~/Desktop/corewar/asm"
corewar = "../corewar"
champions = "../champions/"

championsList = listChampions("s")

for i,v in ipairs(championsList) do
	print(zaz_asm.." "..v)
	for line in io.popen(zaz_asm.." "..v):lines() do
		local tmp1, tmp2, match = line:find("(output)")
		if match then print("Ok")
		else print(line) end
	end
end

championsList = listChampions("cor")

for i,v in ipairs(championsList) do
	errorTable = {}
	a,b, name = v:find(".+/(.+).cor")
	exec(concat(" -n "..v), name)
end
