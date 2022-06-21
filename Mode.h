#pragma once

#include <string>
#include <memory>

class Mode{
	public:
		Mode(const std::string& filter, const std::string& folder);

		const std::string& GetFilter() const;
		const std::string& GetFolder() const;

		virtual const std::string& GetModeName() const = 0;

		void Run();



	protected:
		virtual void RunImpl() = 0;

	private:
		std::string m_Filter;
		std::string m_Folder;

};

class RenameMode final : public Mode{
	public:
		RenameMode(const std::string& filter, const std::string& folder, const std::string& prefix, const int startNumber);

		const std::string& GetModeName() const override;

	protected:
		void RunImpl() override;
	private:
		std::string m_Prefix;
		int m_startNumber;

};

class ArgParser;

std::unique_ptr<Mode> CreateMode(const ArgParser& argparser);


