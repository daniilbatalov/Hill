#include <QCoreApplication>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
using namespace boost::program_options;
#include "hill.h"
#include <iostream>


void conflicting_options(const variables_map& vm, const char* opt1, const char* opt2)
{
    if (vm.count(opt1) && !vm[opt1].defaulted()
        && vm.count(opt2) && !vm[opt2].defaulted())
        throw std::logic_error(std::string("Conflicting options '")
                          + opt1 + "' and '" + opt2 + "'.");
}

void option_dependency(const variables_map& vm,
                        const char* for_what, const char* required_option)
{
    if (vm.count(for_what) && !vm[for_what].defaulted())
        if (vm.count(required_option) == 0 || vm[required_option].defaulted())
            throw std::logic_error(std::string("Option '") + for_what
                              + "' requires option '" + required_option + "'.");
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    try {
        std::string message;
        std::string key;
        bool e_given = false;
        bool d_given = false;
        bool ru_given = false;
        bool en_given = false;
        bool p_given = false;
        std::string alphabet;
        LanguageType l;
        Hill h;
        options_description desc("Allowed options");
        desc.add_options()
        ("help,h", "print usage message")
        ("encrypt,e", bool_switch(&e_given), "encrypt message")
        ("decrypt,d", bool_switch(&d_given), "decrypt message")
        ("message,m", value(&message), "message to encrypt/decrypt")
        ("key,k", value(&key), "key for encryption/decryption")
        ("en", bool_switch(&en_given), "use english alphabet")
        ("ru", bool_switch(&ru_given), "use russian alphabet")
        ("custom", value(&alphabet),"use custom alphabet")
        ("prime,p", bool_switch(&p_given), "make the length of russian or english alphabet prime")
        ;

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);
        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        conflicting_options(vm, "encrypt", "decrypt");

        conflicting_options(vm, "en", "ru");
        conflicting_options(vm, "en", "custom");
        conflicting_options(vm, "custom", "ru");

        conflicting_options(vm, "prime", "custom");
        if(en_given)
        {
            l = EN;
            alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            h = Hill(QString::fromStdString(key), QString::fromStdString(alphabet), l);

        }
        else if(ru_given)
        {
            l = RU;
            alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
            h = Hill(QString::fromStdString(key), QString::fromStdString(alphabet), l);
        }
        else
        {
            l = CUSTOM;
            h = Hill(QString::fromStdString(key), QString::fromStdString(alphabet), l);
        }

        if(p_given)
        {
            h.makePrime();
        }
        if(h.mat.wrong_key)
        {
            throw std::logic_error("Bad key");
        }
        if(e_given)
        {
            QString res = h.encode(QString::fromStdString(message));
            std::cout << "Encrypted message: " << res.toStdString() << std::endl;
        }
        else
        {
           QString res = h.decode(QString::fromStdString(message));
           std::cout << "Decrypted message: " << res.toStdString() << std::endl;;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
    QCoreApplication::exit(0);
    return 0;
}
