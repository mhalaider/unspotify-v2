#pragma once

class c_hooks
{
public:
	void init() const;
	void shutdown() const;
};

inline std::unique_ptr<c_hooks> g_hooks = std::make_unique<c_hooks>();