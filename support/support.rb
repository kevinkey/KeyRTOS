class Dir
    def files(depth = -1, ext = "*")
        f = []
        self.each do |d|
            full_path = File.join(self.path, d)
            if File.directory?(full_path) && !d.start_with?(".")
                if (depth > 0) || (depth < 0)
                    f += Dir.new(full_path).files(depth - 1, ext)
                end
            elsif (File.extname(d) == ext) || (ext == "*")
                f << full_path
            end
        end
        f
    end
end

def cmd(c, desc)
    print "#{desc}... "
    if ENV["ECHO"] == "CMD"
        puts ""
        puts c.join(" ")
    end
    if system(*c)
        puts "success"
    else
        puts "failS"
    end
end
