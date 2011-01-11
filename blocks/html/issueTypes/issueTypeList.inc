<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="interfaceBox">
	<h1><?php
			if (userIsAllowed('IssueTypes')) {
				echo $this->template->linkButton(
					'Add',BASE_URL.'/issueTypes/updateIssueType.php','add'
				);
			}
		?>
		Issue Types
	</h1>
	<table>
		<thead>
			<tr><th></th>
				<th>Type</th>
				<th>Department</th>
				<th>Notes</th>
			</tr>
		</thead>
		<tbody>
		<?php
			foreach ($this->issueTypeList as $issueType) {
				$editButton = '';
				if (userIsAllowed('IssueTypes')) {
					$url = new URL(BASE_URL.'/issueTypes/updateIssueType.php');
					$url->id = $issueType->getId();

					$editButton = $this->template->linkButton(
						'Edit',
						BASE_URL.'/issueTypes/updateIssueType.php?id='.$issueType->getId(),
						'edit'
					);
				}
				$type = View::escape($issueType->getName());
				$department = View::escape($issueType->getDepartment()->getName());
				$notes = count($issueType->getNotes());
				echo "
				<tr><td>$editButton</td>
					<td>$type</td>
					<td>$department</td>
					<td><a href=\"".BASE_URL."/issueTypes/notes.php?issueType_id={$issueType->getId()}\">
							$notes
						</a>
					</td>
				</tr>
				";
			}
		?>
		</tbody>
	</table>
</div>