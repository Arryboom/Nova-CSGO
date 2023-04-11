#include "netvars.h"
#include "interfaces.h"
#include "sdk/ClientClass.h"
#include <format>

void netvars::Setup() noexcept {
	for (ClientClass* clientClass = g_BaseClientDLL->GetAllClasses(); clientClass; clientClass = clientClass->m_pNext)
		if (clientClass->m_pRecvTable)
			Dump(clientClass->m_pNetworkName, clientClass->m_pRecvTable);
}

void netvars::Dump(const char* baseClass, RecvTable* table, unsigned int offset) noexcept {
	for (int i = 0; i < table->propsCount; i++) {
		RecvProp* prop = &table->props[i];

		if (!prop || isdigit(prop->varName[0]))
			continue;

		if (utils::Hash(prop->varName) == utils::HashConst("baseclass"))
			continue;

		if (prop->recvType == SendPropType::DATATABLE &&
			prop->dataTable &&
			prop->dataTable->tableName[0] == 'D')
			Dump(baseClass, prop->dataTable, offset + prop->offset);

		const std::string netvarName = std::format("{}->{}", baseClass, prop->varName);

		netvars::netvars[utils::Hash(netvarName.c_str())] = offset + prop->offset;
	}
}