#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "client.h"
#include "vector.h"

typedef struct {
} workspace_t;

cvector_vector_type(workspace_t *) workspaces;
int active_ws;

workspace_t *ws_curr();
workspace_t *ws_add();
void ws_delete(size_t ws);
void ws_focus(size_t ws);
cvector_vector_type(client_t *) clients_from_ws(size_t ws);

#endif // WORKSPACE_H
