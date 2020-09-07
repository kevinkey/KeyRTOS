$ENV = {"BUILD_DIR" => "./build"}

class Dir
    def dirs(depth = -1)
        d = [self.path]
        self.each do |p|
            full_path = File.join(self.path, p)
            if File.directory?(full_path) && !p.start_with?(".")
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

def include_path(path, depth = -1)
    $ENV["INCLUDE"] = [] if !$ENV.key?("INCLUDE")
    $ENV["INCLUDE"] += Dir.new(path).dirs(depth).map {|i| "-I#{i}"}
end

def compile(c)
    o = File.join($ENV["BUILD_DIR"], c.sub(".c", ".o"))

    FileUtils.mkdir_p(File.dirname(o))
    cmd(["gcc", "-o", o, $ENV["INCLUDE"], "-c", c], "Compile #{File.basename(c)}")

    $ENV["OBJ"] = [] if !$ENV.key?("OBJ")
    $ENV["OBJ"] << o
end

def program(c)
    exe = File.join($ENV["BUILD_DIR"], c.sub(".c", ""))

    FileUtils.mkdir_p(File.dirname(exe))
    cmd(["gcc", "-o", exe, $ENV["INCLUDE"], $ENV["OBJ"], c], "Program #{File.basename(c)}")

    exe
end
