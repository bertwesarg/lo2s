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

#include <lo2s/monitor/process_monitor.hpp>
#include <lo2s/monitor/thread_monitor.hpp>
#include <lo2s/process_info.hpp>

namespace lo2s
{
namespace monitor
{

ProcessMonitor::ProcessMonitor() : MainMonitor()
{
    trace_.register_monitoring_tid(gettid(), "ProcessMonitor", "ProcessMonitor");
}

void ProcessMonitor::insert_process(pid_t pid, pid_t ppid, std::string proc_name, bool spawn)
{
    trace_.process(pid, ppid, proc_name);
    insert_thread(pid, pid, spawn);
}

void ProcessMonitor::insert_thread(pid_t pid, pid_t tid, bool spawn)
{
    if (processes_.count(pid) == 0)
    {
        processes_.emplace(std::piecewise_construct, std::forward_as_tuple(pid),
                           std::forward_as_tuple(pid, spawn));
    }
    if (threads_.count(tid) == 0)
    {
        threads_.emplace(std::piecewise_construct, std::forward_as_tuple(tid),
                         std::forward_as_tuple(pid, tid, *this, processes_.at(pid), spawn));
    }
}

void ProcessMonitor::exit_process(pid_t pid, std::string name)
{
    trace_.process_update_executable(pid, name);
    exit_thread(pid);
}

void ProcessMonitor::exit_thread(pid_t tid)
{
    if (threads_.count(tid) != 0)
    {
        threads_.at(tid).stop();
        threads_.erase(tid);
    }
}

ProcessMonitor::~ProcessMonitor()
{
    for (auto& thread : threads_)
    {
        thread.second.stop();
    }
}
} // namespace monitor
} // namespace lo2s
