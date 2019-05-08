
#include <memory>
#include <string>

#include <libofx/libofx.h>

namespace buba
{
class Database_Project;

class Importer_OFX
{
public:
    Importer_OFX();
    ~Importer_OFX();

    bool process(const std::string& pathname, std::unique_ptr<Database_Project>& dbp);

private:
    LibofxContextPtr m_context = nullptr;
};
}
