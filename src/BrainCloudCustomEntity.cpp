// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudCustomEntity.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
	BrainCloudCustomEntity::BrainCloudCustomEntity(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudCustomEntity::createEntity(const char * in_entityType, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_timeToLive, bool in_isOwned, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);
		message[OperationParam::CustomEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);
		message[OperationParam::CustomEntityServiceTimeToLive.getValue()] = (Json::Int64) in_timeToLive;
		message[OperationParam::CustomEntityServiceIsOwned.getValue()] = in_isOwned;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::CreateEntity, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::deleteEntity(const char * in_entityType,  const char * in_entityId, const std::string& in_jsonEntityData, int32_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::DeleteEntity, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::getCount(const char * in_entityType, const std::string& in_whereJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_whereJson);

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetCount, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::getEntityPage(const char * in_entityType, int32_t in_rowsPerPage, const std::string& in_searchJson, const std::string& in_sortJson, bool in_doCount, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceRowsPerPage.getValue()] = in_rowsPerPage;
		message[OperationParam::CustomEntityServiceSearchJson.getValue()] = JsonUtil::jsonStringToValue(in_searchJson);
		message[OperationParam::CustomEntityServiceSortJson.getValue()] = JsonUtil::jsonStringToValue(in_sortJson);
		message[OperationParam::CustomEntityServiceDoCount.getValue()] = in_doCount;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetEntityPage, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::getEntityPageOffset(const char * in_entityType, const std::string& in_context, int32_t in_pageOffset, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceContext.getValue()] = in_context;
		message[OperationParam::CustomEntityServicePageOffset.getValue()] = in_pageOffset;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetEntityPageOffset, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::readEntity(const char * in_entityType, const char * in_entityId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::ReadEntity, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudCustomEntity::updateEntity(const char * in_entityType, const char * in_entityId, int32_t in_version, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_timeToLive, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;
		message[OperationParam::CustomEntityServiceData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityData);
		message[OperationParam::CustomEntityServiceAcl.getValue()] = JsonUtil::jsonStringToValue(in_jsonEntityAcl);
		message[OperationParam::CustomEntityServiceTimeToLive.getValue()] = (Json::Int64) in_timeToLive;

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateEntity, message, in_callback);
		m_client->sendRequest(sc);
	}
	
	void BrainCloudCustomEntity::updateEntityFields(const char * in_entityType, const char * in_entityId, int32_t in_version, const std::string& in_fieldsJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::CustomEntityServiceEntityType.getValue()] = in_entityType;
		message[OperationParam::CustomEntityServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::CustomEntityServiceVersion.getValue()] = in_version;
		message[OperationParam::CustomEntityFieldsJson.getValue()] = JsonUtil::jsonStringToValue(in_fieldsJson);

		ServerCall * sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateEntityFields, message, in_callback);
		m_client->sendRequest(sc);
	}

}