#include "tree.cpp"

bool check()
{
    for (const auto &enty : fs::directory_iterator(fs::current_path()))
    {

        if (enty.path().filename() == ".pgit")
            return true;
    }
    return false;
}

void init()
{
    if (check())
    {
        std::cout << "pgit already initialised" << std::endl;
        std::cout << fs::current_path();
    }
    else
    {
        auto base = fs::current_path() / fs::path(".pgit");
        fs::create_directories(base);
        fs::create_directories(base / fs::path("diff"));
        fs::create_directories(base / fs::path("file"));
        fs::create_directories(base / fs::path("stage"));
        std::cout << "pgit initialised" << std::endl;
    }
}
int main(int argc, char *argv[])
{
    if(argc==1){
        std::cout<<"enter a command"<<std::endl;
        return 1;
    }


    if (std::strcmp(argv[1], "snapshot") == 0)
    {
        if (!check())
        {
            std::cout << "pgit not initialized" << std::endl;
            return 0;
        }
        if (argc == 3)
        {
            json tree_json;
            if (!fs::exists(fs::current_path() / fs::path(".pgit") / fs::path("tree.json")))
            {
                std::fstream ff;
                ff.open(fs::current_path() / fs::path(".pgit") / fs::path("tree.json"), std::ios::out | std::ios::trunc);
                ff.close();
            }
            std::fstream file((fs::current_path() / fs::path(".pgit") / fs::path("tree.json")).string());
            file.seekg(0, std::ios::end);
            std::streampos size = file.tellg();
            file.seekg(0, std::ios::beg);

            if (size == 0)
            {
                Treeobject new_head = Treeobject(argv[2]);
                new_head.traverse_make_tree_obj(fs::current_path());
                tree_json = new_head.to_json();
                file << tree_json.dump(4); // Write formatted JSON to file
                file.close();
            }

            else
            {
                auto j = loadTreeobject();

                j.snapshot(argv[2]);
            }
        }
        else
        {
            std::cout << "invalid  command" << std::endl;
        }
    }
    else if (std::strcmp(argv[1], "init") == 0)
    {
        if (argc == 2)
        {
            init();
        }
        else
        {
            std::cout << "invalid command" << std::endl;
        }
    }
    else if (std::strcmp(argv[1], "rollback") == 0)
    {
        if (argc == 3)
        {
            if (!fs::exists(fs::current_path() / fs::path(".pgit") / fs::path("tree.json")))
            {
                std::fstream ff;
                ff.open(fs::current_path() / fs::path(".pgit") / fs::path("tree.json"), std::ios::out | std::ios::trunc);
                ff.close();
            }
            std::fstream file((fs::current_path() / fs::path(".pgit") / fs::path("tree.json")).string());
            file.seekg(0, std::ios::end);
            std::streampos size = file.tellg();
            file.seekg(0, std::ios::beg);
            if (size == 0)
            {
                std::cout << "no commits made to roll back" << std::endl;
            }
            else
            {
                auto j = loadTreeobject();

                j.roll_back(argv[2]);
            }
        }
        else
        {
            std::cout << "invalid  command" << std::endl;
        }
    }
    else if (std::strcmp(argv[1], "log") == 0)
    {
        if (argc == 2)
        {
            if (!fs::exists(fs::current_path() / fs::path(".pgit") / fs::path("tree.json")))
            {
                std::fstream ff;
                ff.open(fs::current_path() / fs::path(".pgit") / fs::path("tree.json"), std::ios::out | std::ios::trunc);
                ff.close();
            }
            std::fstream file((fs::current_path() / fs::path(".pgit") / fs::path("tree.json")).string());
            file.seekg(0, std::ios::end);
            std::streampos size = file.tellg();
            file.seekg(0, std::ios::beg);
            if (size == 0)
            {
                std::cout << "no commits exists" << std::endl;
            }
            else
            {
                auto j = loadTreeobject();

                j.log();
            }
        }
        else
        {
            std::cout << "invalid  command" << std::endl;
        }
    }
     
    else{
        std::cout<<"invalid command"<<std::endl;
    }
}