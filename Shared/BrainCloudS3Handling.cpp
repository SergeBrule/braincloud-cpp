#include "BrainCloudS3Handling.h"
#include "BrainCloudClient.h"
#include "StringUtil.h"


namespace BrainCloud
{
    void BrainCloudS3Handling::getUpdatedFiles(const char * in_category, const char * in_fileDetails, IServerCallback * in_callback )
    {
        Json::Value message;
        Json::Reader reader;
        
        if (StringUtil::IsOptionalParameterValid(in_category))
        {
            message[OperationParam::S3HandlingServiceCategory.getValue()] = in_category;
        }
        
        Json::Value parsedDetails;
        reader.parse(in_fileDetails, parsedDetails);
        
        message[OperationParam::S3HandlingServiceFileDetails.getValue()] = parsedDetails;
        ServerCall * sc = new ServerCall( ServiceName::S3Handling, ServiceOperation::GetUpdatedFiles, message, in_callback );
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
    }
    
    void BrainCloudS3Handling::getFileList(const char * in_category, IServerCallback * in_callback )
    {
        Json::Value message;
        
        if (StringUtil::IsOptionalParameterValid(in_category))
        {
            message[OperationParam::S3HandlingServiceCategory.getValue()] = in_category;
        }
        
        ServerCall * sc = new ServerCall( ServiceName::S3Handling, ServiceOperation::GetFileList, message, in_callback );
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
    }
}