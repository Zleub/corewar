array = Array.new

class String
	def numeric?
		Float(self) != nil rescue false
	end
end

if ARGV.empty?
	ARGV[0] = "1"
end

if not ARGV[0].numeric?
	puts "Error."
	exit
end

Dir.foreach("./champions") do |fichier|
	if fichier != "." and fichier != ".."
		array.push(fichier)
	end
end

array = array.combination(ARGV[0].to_i).to_a

array.each do |x|
	mystring = "";
	x.each { |y| mystring += "-n champions/" + y + " " }
	puts mystring
end
