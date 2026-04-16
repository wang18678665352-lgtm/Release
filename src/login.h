#ifndef LOGIN_H
#define LOGIN_H

#include "common.h"
#include "data_storage.h"

// Login function - returns 0 on success, error code on failure
int login(User *logged_user);

// Register new user - returns 0 on success, error code on failure
int register_user(User *new_user);

// Logout function
void logout(Session *session);

// Check user permission
bool has_permission(const User *user, const char *required_role);

#endif // LOGIN_H
