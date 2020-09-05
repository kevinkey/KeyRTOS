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

build_dir = "./Build"
tests, sources = Dir.new(".").files(-1, ".c").partition {|f| f.end_with?("_test.c")}
objects = []

task :clobber do
    FileUtils.rm_rf(build_dir)
end

task :build do
    sources.each do |c|
        o = File.join(build_dir, c.sub(".c", ".o"))
        objects << o
        FileUtils.mkdir_p(File.dirname(o))
        system(*["gcc", "-o", o, "-c", c])
    end
end

task :test => :build do
    tests.each do |t|
        exe = File.join(build_dir, t.sub(".c", ""))
        system(*["gcc", "-o", exe, objects].flatten, t)
        system(exe)
    end
end