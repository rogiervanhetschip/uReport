<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Ticket $this->ticket
 * @param bool $this->disableButtons
 */
$location = View::escape($this->ticket->getLocation());
$location = $location
	? "<a href=\"".BASE_URL."/locations/view?location=".urlencode($location)."\">$location</a>"
	: '';

if (userIsAllowed('people','view')) {
	$url = new URL(BASE_URL.'/people/view.php');
	$personFields = array('enteredBy','assigned','referred');
	foreach ($personFields as $field) {
		$$field = '';
		$get = 'get'.ucfirst($field).'Person';
		$person = $this->ticket->$get();
		if ($person) {
			$url->person_id = "{$person->getId()}";
			$$field = "<a href=\"$url\">".View::escape($person->getFullname())."</a>";
		}

	}
}

$status = $this->ticket->getStatus();
if ($this->ticket->getSubstatus()) {
	$status.= ': '.$this->ticket->getSubstatus();
}

$editStatusButton     = '';
$deleteButton         = '';
$changeCategoryButton = '';
$changeLocationButton = '';
$assignButton         = '';
$referralButton       = '';

if (!$this->disableButtons && userIsAllowed('tickets','update')) {
	$editStatusButton = "
	<a class=\"icon-pencil\"
		href=\"".BASE_URI."/tickets/changeStatus?ticket_id={$this->ticket->getId()}\">
		<span class=\"hidden-label\">Change Status</span>
	</a>
	";
	if (userIsAllowed('tickets', 'delete')) {
		$deleteButton = "
		<a class=\"btn\"
			href=\"".BASE_URI."/tickets/delete?ticket_id={$this->ticket->getId()}\">
			<span class=\"icon-remove\"></span>
			Delete Case
		</a>
		";
	}

	if ($this->ticket->getStatus()!='closed') {
		$changeCategoryButton = "
		<a class=\"icon-pencil\"
			href=\"".BASE_URI."/tickets/changeCategory?ticket_id={$this->ticket->getId()}\">
			<span class=\"hidden-label\">Change Category</span>
		</a>
		";
		$changeLocationButton = "
		<a class=\"icon-pencil\"
			href=\"".BASE_URI."/tickets/changeLocation?ticket_id={$this->ticket->getId()}\">
			<span class=\"hidden-label\">Change Location</span>
		</a>
		";
		if (userIsAllowed('people','view')) {
			$assignButton = "
			<a class=\"icon-pencil\"
				href=\"".BASE_URI."/tickets/assign?ticket_id={$this->ticket->getId()}\">
				<span class=\"hidden-label\">Assign</span>
			</a>
			";

			$return_url = $this->ticket->getURL();
			$referralButton = "
			<a class=\"icon-pencil\"
				href=\"".BASE_URI."/tickets/refer?ticket_id={$this->ticket->getId()}\">
				<span class=\"hidden-label\">Refer</span>
			</a>
			";
		}
	}

}

$category = $this->ticket->getCategory_id()
	? View::escape($this->ticket->getCategory()->getName())
	: '';
echo "
<div class=\"ticketInfo twoColumnlist\">
	<h2><a href=\"{$this->ticket->getURL()}\">Case #{$this->ticket->getId()}</a> $deleteButton</h2>
	<ul>
		<li><label>Category:</label>
			$category
			$changeCategoryButton
		</li>
		<li><label>Location:</label>
			$location
			$changeLocationButton
		</li>
		<li><label>Status:</label>
			$status
			$editStatusButton
		</li>
";
if (userIsAllowed('people','view')) {
	echo "
		<li><label>Assigned To:</label>
			$assigned
			$assignButton
		</li>
		<li><label>Referred To:</label>
			$referred
			$referralButton
		</li>
		<li><label>Created By:</label>
			$enteredBy
		</li>
	";
}
	$client = $this->ticket->getClient();
	if ($client) {
		$name = View::escape($client->getName());
		echo "
		<li>
			<label>Received Via:</label>
			$name
		</li>
		";
	}
echo "
		<li><label>Date Opened:</label>
			{$this->ticket->getEnteredDate(DATE_FORMAT)}
		</li>
		<li><label>Date Closed:</label>
			{$this->ticket->getClosedDate(DATE_FORMAT)}
		</li>
		<li><label>Last Modified:</label>
			{$this->ticket->getLastModified(DATE_FORMAT)}
		</li>
	</ul>
</div>
<script type=\"text/javascript\">
	CRM.ticket_id = {$this->ticket->getId()};
</script>
";
$this->template->addToAsset('scripts',YUI.'/yui/yui-min.js');
$this->template->addToAsset('scripts',BASE_URI.'/js/tickets/actionForms.js');
