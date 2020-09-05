require_relative "support/build.rb"

build_dir = "./build"
includes = (["support"] + Dir.new("source").dirs(-1)).map {|i| "-I#{i}"}
sources = Dir.new("source").files(-1, ".c")
tests = Dir.new("test").files(-1, ".c")
objects = []

task :clobber do
    FileUtils.rm_rf(build_dir)
end

task :build do
    sources.each do |c|
        o = File.join(build_dir, c.sub(".c", ".o"))
        objects << o
        FileUtils.mkdir_p(File.dirname(o))
        cmd(["gcc", "-o", o, includes, "-c", c], "Compile #{File.basename(c)}")
    end
end

task :test => :build do
    tests.each do |t|
        exe = File.join(build_dir, t.sub(".c", ""))
        FileUtils.mkdir_p(File.dirname(exe))
        cmd(["gcc", "-o", exe, includes, objects, t], "Build #{File.basename(t)}")
        cmd([exe], "Run #{File.basename(t)}")
    end
end
