inspect = require 'inspect'

function fclean() os.execute("make -C .. fclean") end
function make() os.execute("make -C ..") end
function re() fclean() make() end

corewar = "../corewar"
champions = "../champions/"

function listChampions()
	local i, t, popen = 0, {}, io.popen
	for filename in popen('ls -a "'..champions..'" | grep \\.cor'):lines() do
		i = i + 1
		t[i] = champions..filename
	end
	return t
end

championsList = listChampions()

function getChampion(nbrChampions)
	math.randomseed(os.time())

	local str = ""
	for i=1, nbrChampions do
		local nbr = math.random(#championsList)
		str = str.." -n "..championsList[nbr]

	end
	return str
end

function exec(nbrChampions)
	print("../corewar"..getChampion(nbrChampions))
	-- os.execute("../corewar"..getChampion(nbrChampions))
	local i = 1
	for lines in io.popen("../corewar"..getChampion(nbrChampions)):lines() do
		print('['..i..'] '..lines)
		i = i + 1
	end
end

exec(1)
