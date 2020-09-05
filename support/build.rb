class Dir
    def dirs(depth = -1)
        d = []
        self.each do |p|
            full_path = File.join(self.path, p)
            if File.directory?(full_path) && !p.start_with?(".")
                d << full_path
                if (depth > 0) || (depth < 0)
                    d += Dir.new(full_path).dirs(depth - 1)
                end
            end
        end
        d
    end
    def files(depth = -1, ext = "*")
        f = []
        self.each do |p|
            full_path = File.join(self.path, p)
            if File.directory?(full_path) && !p.start_with?(".")
                if (depth > 0) || (depth < 0)
                    f += Dir.new(full_path).files(depth - 1, ext)
                end
            elsif (File.extname(p) == ext) || (ext == "*")
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
    if system(*c.flatten)
        puts ""
    else
        puts "fail!"
    end
end
