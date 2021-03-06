/*
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#import <ComponentKit/CKDefines.h>

#if CK_NOT_SWIFT

#import <Foundation/Foundation.h>

#import <ComponentKit/CKAction.h>
#import <vector>


/** It's necessary to specify a list of selectors your delegate will implement, because we have to answer the question "respondsToSelector:" without access to the responder chain, since it's is frequently cached as an optimization in objects with delegates. */

using CKComponentForwardedSelectors = std::vector<SEL>;

std::string CKIdentifierFromDelegateForwarderSelectors(const CKComponentForwardedSelectors& first);


/**
 This class is intended for ComponentKit internal use only.
 */
@interface CKComponentDelegateForwarder : NSObject

/**
 This initializer will make an object that forwards calls to the given selectors on to the component, and its nextResponder, etc.
 */
+ (instancetype _Nullable)newWithSelectors:(CKComponentForwardedSelectors)selectors;

/**
 The view is used to find out where to start looking in the component responder chain.

 The forwarder will call [CKMountedComponentForView(view) targetForAction: withSender:] to proxy to the responder chain, so this needs to be accurate when you mount/unmount.
 */
@property (nonatomic, weak) UIView * _Nullable view;

@end

NS_ASSUME_NONNULL_BEGIN

auto CKDelegateProxyForObject(NSObject *obj) -> CKComponentDelegateForwarder *_Nullable;
auto CKSetDelegateProxyForObject(NSObject *obj, CKComponentDelegateForwarder *_Nullable delegateProxy) -> void;

NS_ASSUME_NONNULL_END

#endif
