/*
 * This file is part of the lo2s software.
 * Linux OTF2 sampling
 *
 * Copyright (c) 2016,
 *    Technische Universitaet Dresden, Germany
 *
 * lo2s is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * lo2s is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lo2s.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <lo2s/monitor/main_monitor.hpp>

#include <lo2s/monitor/core_monitor.hpp>

#include <lo2s/monitor_config.hpp>

#include <map>

namespace lo2s
{
namespace monitor
{

class GlobalMonitor : public MainMonitor
{
public:
    GlobalMonitor(const MonitorConfig& config);
    ~GlobalMonitor();

    void run();

private:
    std::map<int, CoreMonitor> monitors_;
};
}
}