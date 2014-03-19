//
//  MessagePackParser_Internal.h
//  WithBuddiesBase
//
//  Created by odyth on 3/18/14.
//  Copyright (c) 2014 scopely. All rights reserved.
//

#import <WithBuddiesBase/MessagePackParser.h>
#include "msgpack_src/msgpack.h"

@interface MessagePackParser () {
    // This is only for MessagePackParser+Streaming category.
    msgpack_unpacker unpacker;
}

@end
