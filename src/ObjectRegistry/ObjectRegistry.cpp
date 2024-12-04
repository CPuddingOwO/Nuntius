#include <Nuntius/ObjectRegistry/ObjectRegistry.hpp>
#include <Nuntius/API.hpp>

NT_API std::unordered_map<std::type_index, std::shared_ptr<void>>  nt::ObjectRegistry::registry;
NT_API std::mutex                                                  nt::ObjectRegistry::mutex_;
