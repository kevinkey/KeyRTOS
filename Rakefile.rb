require_relative "support/support.rb"

build_dir = "./build"
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
        cmd(["gcc", "-o", o, "-c", c], "Compile #{File.basename(c)}")
    end
end

task :test => :build do
    tests.each do |t|
        exe = File.join(build_dir, t.sub(".c", ""))
        cmd(["gcc", "-o", exe, "-ISupport", objects, t].flatten, "Build #{File.basename(t)}")
        cmd([exe], "Run #{File.basename(t)}")
    end
end
